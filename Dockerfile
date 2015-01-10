FROM debian:jessie

MAINTAINER ReanGD

ENV DEBIAN_FRONTEND noninteractive
ENV LANG ru_RU.UTF-8

RUN echo en_US.UTF-8 UTF-8 > /etc/locale.gen && \
    echo ru_RU.UTF-8 UTF-8 >> /etc/locale.gen && \
    \
    apt-get update && \
    apt-get install -y curl locales && \
    \
    curl -o /tmp/btsync.tar.gz http://download.getsyncapp.com/endpoint/btsync/os/linux-x64/track/stable && \
    tar -xf /tmp/btsync.tar.gz -C /usr/bin && \
    rm /tmp/btsync.tar.gz && \
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
    rm -rf /usr/share/locale/ && \
    rm -rf /usr/share/man/ && \
    rm -rf /usr/sbin/locale-gen && \
    rm -rf /usr/sbin/update-locale && \
    rm -rf /usr/sbin/validlocale

ADD run.sh /home/run.sh

EXPOSE 8080
EXPOSE 50000/udp

VOLUME ["/btsync"]

CMD /home/run.sh