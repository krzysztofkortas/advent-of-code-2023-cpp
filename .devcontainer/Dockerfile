FROM happycerberus/devenv-trunk:20240118

# zip - needed by vcpkg
RUN set -ex; \
    apt-get update; \
    apt-get install -y zip;

# vcpkg
RUN set -ex;\
    git -C /usr/src clone https://github.com/microsoft/vcpkg.git;\
    ./usr/src/vcpkg/bootstrap-vcpkg.sh;

ENV VCPKG_ROOT=/usr/src/vcpkg
ENV PATH="${VCPKG_ROOT}:${PATH}"
