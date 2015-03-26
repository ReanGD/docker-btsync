FROM debian:jessie

MAINTAINER ReanGD

ENV DEBIAN_FRONTEND noninteractive
ENV LANG ru_RU.UTF-8
ENV LANGUAGE ru_RU.UTF-8

ADD https://download-cdn.getsyncapp.com/stable/linux-x64/BitTorrent-Sync_x64.tar.gz /home/btsync.tar.gz
ADD run.sh /home/run.sh
ADD btsync.conf /home/btsync.conf

RUN echo en_US.UTF-8 UTF-8 > /etc/locale.gen && \
    echo ru_RU.UTF-8 UTF-8 >> /etc/locale.gen && \
    \
    apt-get update && \
    apt-get install -y locales && \
    \
    tar -xf /home/btsync.tar.gz -C /home && \
    rm /home/btsync.tar.gz && \
    \
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

EXPOSE 8080
EXPOSE 50000/udp

VOLUME ["/btsync"]

CMD /home/run.sh