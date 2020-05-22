#ifndef DNSCONF_H
#define DNSCONF_H

#include "time.h"

#include <string>
#include <vector>

struct SiteGroup
{
	std::vector<std::string> URLs;
	std::vector<TimeRange> allowedAt;
};

using RuleSet = std::vector<SiteGroup>;

std::string urlToDNSEntry(const std::string &url);		// address=/example.com/ is the syntax for blocking a website in dnsmasq.conf
														// address=/example.com/redirect.to can be used instead for redirecting.

bool ignoreEntryGroup(const std::vector<TimeRange> &allowedTimes);
void addSiteGroupURLs(std::string &config, const SiteGroup &sg);

std::string getUpdatedConfig();		// Generates the dnsmasq.conf content to block and allow desired sites.

#endif
