#!/bin/bash

set -e

[ ! -f /btsync/btsync.conf ] && cat > /btsync/btsync.conf <<EOF
{ 
  "device_name": "Sync Server",
  "listening_port" : 50000,
  "storage_path" : "/btsync",
  "pid_file" : "/btsync/btsync.pid",
  "check_for_updates" : false,
  "use_upnp" : false,
  "download_limit" : 0,
  "upload_limit" : 0,
  "webui" :
  {
    "listen" : "0.0.0.0:8080",
    "login" : "admin",
    "password" : "admin"
  },
  "shared_folders" :
  [
    {
      "secret" : "$SECRET1",
      "dir" : "/media/AudioBook",
      "use_relay_server" : false, 
      "use_tracker" : false, 
      "search_lan" : false,
      "use_dht" : false,
      "known_hosts" :
      [
      ]
    }
   ]
}
EOF
mkdir -p /btsync
mkdir -p /media/AudioBook
/usr/bin/btsync --nodaemon --log /btsync/btsync.log --config /btsync/btsync.conf