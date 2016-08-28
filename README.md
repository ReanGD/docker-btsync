docker-btsync
===

The docker image with btsync on Alpine Linux.

```
docker run -d --name=btsync -p 80:80 -v /home/btsync:/btsync -v /etc/localtime:/etc/localtime:ro reangd/btsync:latest
```
