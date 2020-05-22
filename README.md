# DNSMASQ Manager

Simple program to block websites at predefined desired times. **It requires [dnsmasq](http://www.thekelleys.org.uk/dnsmasq/doc.html) and [systemd](https://systemd.io/).**

## Setup
#### Configuring files
Firstly, open up `dnsconf.cpp` and define *Domain Name Servers*, *SiteGroups* and add these to *RuleSet*. You can follow the example.
It is also possible to set a website to be redirected to upon blocking.

Then you can set your desired refresh time over at `main.cpp` by setting *SECONDS_TO_REFRESH*.
In the current version, setting this number too high might be counter-productive.

Let's say you want to block access to **youtube.com** at **20:00**.
With `SECONDS_TO_REFRESH{ 60 * 60 }` *(one hour)* **youtube.com** could potentially get blocked at **20:59**, which is a whole hour of potential ditraction!

I might change this in the future *(if anyone wants to)*, but for the time being, and because I set `SECONDS_TO_REFRESH{ 5 }`, I have no problems with this setup.

#### Installing
Run:
```
$ make release
# mv -nv main /usr/bin/dnsmasq-manager
```

#### Enabling the service
Now you need to create *.service* file for systemd. You can use `dnsmasq-manager.service`.
Install it with:
```
# cp dnsmasq-manager.service /etc/systemd/system/
# systemctl enable --now dnsmasq-manager.service
```

You may optionally want to add a dependency of **dnsmasq** to **dnsmasq-manager** by appending the following line to the *Unit* section of `dnsmasq.service` *(I have provided a sample file as well)*:
```
[Unit]
...
BindsTo=dnsmasq-manager.service
```
The service file is probably located at `/usr/lib/systemd/system/dnsmasq.service`.
If you do bind **dnsmasq** to **dnsmasq-manager**, then you don't need **dnsmasq-manager.service** to be enabled as **dnsmasq.service** will start and stop it automatically.

### Contact
For any issues and suggestions contact me: agna.lumi@protonmail.com
