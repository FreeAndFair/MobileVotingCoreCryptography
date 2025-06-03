#####################################################################
# Dockerfile for the Free&Fair CPV DE/PLE Docker image (cpv-e2eviv) #
#                                                                   #
# @author Daniel M. Zimmerman                                       #
# @copyright 2025 Free & Fair                                       #
# @version 2025-06-06                                               #
#####################################################################

# The use of TARGETARCH here avoids a Docker warning about selecting a
# static build architecture.
FROM --platform=${TARGETARCH} ubuntu:25.04 AS base

RUN apt-get clean && \
    apt-get update && \
    apt-get upgrade -y && \
    apt-get clean

# First, install Tamarin and Maude into an image that we can then
# extract them from to save space.
FROM base AS dependencies

ENV TAMARIN_VERSION=1.10.0
ENV TAMARIN_URL=https://github.com/tamarin-prover/tamarin-prover/releases/download/${TAMARIN_VERSION}/tamarin-prover-${TAMARIN_VERSION}-linux64-ubuntu.tar.gz
ENV MAUDE_VERSION=3.5
ENV MAUDE_URL=https://github.com/maude-lang/Maude/releases/download/Maude${MAUDE_VERSION}/Maude-${MAUDE_VERSION}-linux-x86_64.zip

RUN apt-get install -y curl zip

RUN mkdir -p /dependencies && \
    curl -q -s -S -L --create-dirs -o maude.zip ${MAUDE_URL} && \
    unzip maude.zip -d /dependencies && \
    curl -q -s -S -L --create-dirs -o tamarin.tar.gz ${TAMARIN_URL} && \
    tar -x -C /dependencies -f tamarin.tar.gz && \
    chmod -R +x /dependencies

# Next, create the runtime image and copy the dependencies in.
FROM base AS runtime

COPY --from=dependencies /dependencies /usr/local/bin

RUN apt-get install -y graphviz locales && \
    apt-get clean

# Set up environment for Unicode.
RUN echo "en_US.UTF-8 UTF-8" >> /etc/locale.gen
RUN locale-gen en_US.UTF-8
ENV LC_ALL="en_US.UTF-8"

# Create and run as non-root user
RUN groupadd -g 1001 cpv
RUN useradd -m -u 1001 -g 1001 cpv
USER cpv

# Set the default working directory.
WORKDIR /home/cpv

# Passed to and executed by startup.sh.
CMD ["/bin/bash"]
