#!/bin/sh

set -e

[ ! -f /btsync/btsync.conf ] && cp /etc/btsync.conf /btsync
btsync --nodaemon --log /btsync/btsync.log --config /btsync/btsync.conf