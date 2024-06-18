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

# NOTE: We have to run the configure step and the build step together
#       because /src/build is bind-mounted to the host machine, and that
#       needs to occur before the configure step is run or else the
#       files are obscured.

CMD cmake --preset release && cmake --build --preset release
