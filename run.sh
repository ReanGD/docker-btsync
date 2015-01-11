#!/bin/bash

set -e

mkdir -p /btsync
[ ! -f /btsync/btsync.conf ] && cp /home/btsync.conf /btsync
/home/btsync --nodaemon --log /btsync/btsync.log --config /btsync/btsync.conf