FROM ubuntu

RUN apt-get update \
    && apt-get install -y gcc make

WORKDIR /project323