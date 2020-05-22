/* DNS-MANAGER
 *
 * Sets scheduled times for certain websites to be available, and enforces them strictly.
 * Depends on systemd and dnsmasq.
 *
 */

#include "dnsconf.h"
#include "file.h"
#include "shell.h"

#include <iostream>
#include <string>
#include <unistd.h>

constexpr int SECONDS_TO_REFRESH{ 60 * 5 };

const std::string DNSMASQ_CONF_PATH{ "/etc/dnsmasq.conf" }; // These are good default values
const std::string DNSMASQ_SERVICE{ "dnsmasq.service" };		//
															//
const std::string RESOLV_CONF_PATH{ "/etc/resolv.conf" };	//
const std::string RESOLV_CONF{ "nameserver 127.0.0.1" };	//

int main()
{
	while (true)
	{
		overwriteFile(RESOLV_CONF_PATH, RESOLV_CONF);			// Ensures dnsmasq is the only dns in use.
		if (unitIsHealthy(DNSMASQ_SERVICE))
		{
			std::cout << DNSMASQ_SERVICE << " is healthy.\n";

 			std::string configContent{ getUpdatedConfig() }; 
 			overwriteFile(DNSMASQ_CONF_PATH, configContent);

 			refreshUnit(DNSMASQ_SERVICE);
			std::cout << "Service updated.\n";
		}
		else
		{
			std::cerr << "Error: Unit has failed.\n";
			break;
		}
		sleep( SECONDS_TO_REFRESH );
	}
	return 0;
}
