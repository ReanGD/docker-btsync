FROM debian:jessie

MAINTAINER ReanGD

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update && \
    apt-get install -y curl && \
    \
    curl -o /tmp/btsync.tar.gz http://download.getsyncapp.com/endpoint/btsync/os/linux-x64/track/stable && \
    tar -xf /tmp/btsync.tar.gz -C /usr/bin && \
    rm /tmp/btsync.tar.gz && \
    mkdir -p /btsync/storage && \   
    \
    apt-get purge -y curl && \
    apt-get autoremove -y && \
    apt-get clean && \
    rm -rf /var/cache/apt/* && \
    rm -rf /var/lib/apt/* && \
    rm -rf /var/lib/dpkg/* && \
    rm -rf /var/lib/cache/* && \
    rm -rf /var/lib/log/* && \
    rm -rf /usr/share/i18n/ && \
    rm -rf /usr/share/doc/ && \
    rm -rf /usr/share/man/

ADD run.sh /home/run.sh

EXPOSE 8080
EXPOSE 50000/udp

VOLUME ["/btsync"]

CMD /home/run.sh