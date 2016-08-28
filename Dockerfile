FROM alpine:edge

MAINTAINER ReanGD

ADD run.sh /bin/run.sh
ADD btsync.conf /etc/btsync.conf

RUN apk --no-cache add curl && \
	curl -L https://download-cdn.getsync.com/stable/linux-x64/BitTorrent-Sync_x64.tar.gz | tar xz -C /bin && \
	curl -L https://github.com/sgerrand/alpine-pkg-glibc/releases/download/2.23-r3/glibc-2.23-r3.apk -o glibc-2.23-r3.apk && \
	apk add --allow-untrusted glibc-2.23-r3.apk && \
	rm glibc-2.23-r3.apk

EXPOSE 80

VOLUME ["/btsync"]

CMD run.sh