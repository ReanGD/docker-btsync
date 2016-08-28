FROM alpine:edge

MAINTAINER ReanGD

ADD run.sh /bin/run.sh
ADD btsync.conf /etc/btsync.conf

RUN apk --no-cache add curl && \
	curl -L https://download-cdn.getsync.com/stable/linux-glibc-x64/BitTorrent-Sync_glibc23_x64.tar.gz | tar xz -C /bin && \
	rm /bin/README /bin/LICENSE.TXT

EXPOSE 80

VOLUME ["/btsync"]

CMD run.sh