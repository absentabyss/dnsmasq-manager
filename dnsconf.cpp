#include "dnsconf.h"
#include "time.h"

#include<ctime>
#include<string>
#include<vector>

const std::string DNSMASQ_CONF_HEAD
{
	"listen-address=::1,127.0.0.1\n"	// Do not change this line.

	"server=1.1.1.1\n"					// Add all your desired DNSs from this point on.
	"server=8.8.8.8\n"					// Without valid DNSs you won't have internet connection at all.
										// The example I give works just fine. If you don't know what to do
										// just leave it as is.
};

/* You can copy paste this and replace <category name>, <urls> and <TimeRanges> like the example below.
 * v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v 
 * const SiteGroup <category name>
 * {
 * 		{<urls>},
 * 		{
 * 			<TimeRanges>
 * 		}
 * }
 * ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^  
 */

const SiteGroup chats		// This is an example I personally use. I first define a category of sites to manage.
{
	{"discord.com", "telegram.org", "whatsapp.com"},	// Then define all the URLs pertaining to the group separated by commas.
	{
		TimeRange{ getTM(3, 30, 0), getTM(4, 30, 0) },		// And here comes the list of allowed times separated by commas.
		TimeRange{ getTM(7, 45, 0), getTM(8, 0, 0) },		// This can be read as TimeRange{ <local time to start allowing>, <local time to start blocking> }
		TimeRange{ getTM(8, 20, 0), getTM(8, 35, 0) },		// And times are of the format getTM(hour, minute, second).
		TimeRange{ getTM(14, 15, 0), getTM(14, 30, 0) },
		TimeRange{ getTM(14, 50, 0), getTM(15, 05, 0) },
		TimeRange{ getTM(22, 45, 0), getTM(23, 0, 0) },
	}
};

const SiteGroup permaBlocked 		// Define as many SiteGroups as you need.
{
	{
		"sexysites.com",
		"stuffidontwantmydaughtertosee.com",
		"yougettheidea.com",
	},
	{}		// Because there are no allowed times set, this works like a permanent blocker. It's good for parental protection.
};

const SiteGroup youtube
{
	{ "nicovideo.jp", "youtube.com", "twitch.tv" },		// Sometimes videos can consume your life. And it's good to limit their usage to certain times.
	{
		TimeRange{ getTM(3, 30, 0), getTM(4, 30, 0) },
		TimeRange{ getTM(22, 0, 0), getTM(23, 0, 0) },
	}
};

const RuleSet rules{ chats, permaBlocked, youtube };		// Make sure to add all your SiteGroups here.
															// Otherwise, they will be ignored (i.e. the websites won't ever be blocked).

std::string urlToDNSEntry(const std::string &url)		// Can also redirect instead of blocking.
{
	std::string entry{ "address=/" };
//	entry += url + "/redirect.to/"		// Replace line below with this one to redirect and replace "redirect.to" with a valid url.
	entry += url + "/\n";
	return entry;
}

bool ignoreEntryGroup(const std::vector<TimeRange> &allowedTimes)		// Determines whether a SiteGroup should be allowed at time of execution.
{																		// the EntryGroup is *ignored* from being blocked at dnsmasq.conf
	std::time_t time{};
	std::time(&time);
	std::tm localtime{ *std::localtime(&time) };
	bool ignore{};
	for (TimeRange tr: allowedTimes)
	{
		if (isBetweenPeriod(localtime, tr.earlyEnd, tr.lateEnd))
			ignore = true;
	}
	return ignore;
}

void addSiteGroupURLs(std::string &config, const SiteGroup &sg)
{
	for (std::string url: sg.URLs)
	{
		config += urlToDNSEntry(url);
	}
	return;
}

std::string getUpdatedConfig()
{
	std::string config{ DNSMASQ_CONF_HEAD };
	for (SiteGroup sg: rules)
	{
		if (!ignoreEntryGroup(sg.allowedAt))
			addSiteGroupURLs(config, sg);
	}
	return config;
}
