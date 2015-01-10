#!/bin/bash

set -e

[ ! -f /btsync/btsync.conf ] && cat > /btsync/btsync.conf <<EOF
{ 
  "device_name": "Sync Server",
  "listening_port" : 50000,
  "storage_path" : "/btsync/storage",
  "pid_file" : "/btsync/storage/btsync.pid",
  "check_for_updates" : false,
  "use_upnp" : false,
  "download_limit" : 0,
  "upload_limit" : 0,
  "webui" :
  {
    "listen" : "0.0.0.0:8080",
    "login" : "admin",
    "password" : "admin"
  }
}
EOF

/btsync --nodaemon --log /btsync/btsync.log --config /btsync/btsync.conf