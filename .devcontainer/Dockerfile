FROM krzysztofkortas/devenv-trunk:latest

ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# Create the user
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && chown -R $USERNAME /home/$USERNAME \
    # Add sudo support.
    && apt-get update \
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

USER $USERNAME

# zip - needed by vcpkg
RUN set -ex; \
    sudo apt-get update; \
    sudo apt-get install -y zip;

# vcpkg
RUN set -ex;\
    cd;\
    git clone https://github.com/microsoft/vcpkg.git;\
    ./vcpkg/bootstrap-vcpkg.sh;

ENV VCPKG_ROOT=/home/$USERNAME/vcpkg
ENV PATH="${VCPKG_ROOT}:${PATH}"

# cmake-format
RUN set -ex; \
    sudo apt-get update; \
    sudo apt-get install -y cmake-format
