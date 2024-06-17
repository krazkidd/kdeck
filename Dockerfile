FROM debian:latest

RUN apt-get update && apt-get -y --no-install-recommends --no-install-suggests install \
    build-essential \
    cmake \
    libcurlpp-dev \
    libboost-json1.81-dev \
    libwxgtk3.2-dev \
    && apt-get clean \
    && rm -r /var/lib/apt/lists /var/cache/apt

WORKDIR /src
COPY . /src

RUN mkdir /src/build

RUN cmake --preset release

ENTRYPOINT ["cmake", "--build", "--preset", "release", "--"]
