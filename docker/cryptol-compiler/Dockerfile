################################################################################
# Dockerfile for Free & Fair Cryptol Compiler Docker image (amd64 & arm64/v8)  #
# @author Frank Zeyda                                                          #
# @copyright 2025 Free & Fair                                                  #
# @version 2025-06-16                                                          #
################################################################################

# Recommended versions of dependencies by `cryptol-compiler` (see README.md):
# - ghc-9.4 (we shall use ghc-9.4.8, the most recent ghc-9.4._)
# - cabal-3.8
# - Z3 4.8.14 (we shall use Z3 4.15.1, the June 10, 2025 release)
# (These are the ones tested against by the respective CI actions.)

################################################################################
# Global ARGs
################################################################################

# Git tag of the cryptol-compiler release; provided by Makefile.
ARG CRYPTOL_COMPILER_TAG

# Installation directory for the cryptol-compiler binary.
ARG CRYPTOL_COMPILER_INSTALL_DIR="/opt/cryptol-compiler-${CRYPTOL_COMPILER_TAG}/bin"

################################################################################
# Stage: build (builds the cryptol-compiler binary from source)
################################################################################

# Image used to build `cryptol-compiler` from the repository clone.
FROM --platform=${TARGETARCH} haskell:9.4.8 AS build

# Installation directory for the cryptol-compiler binary.
ARG CRYPTOL_COMPILER_INSTALL_DIR

# Copy fresh clone of the source repository into build image.
COPY repositories/cryptol-compiler /repos/cryptol-compiler

# Use cabal to compiler and install cryptol-compiler binary.
RUN cd /repos/cryptol-compiler && \
    cabal v2-update            && \
    cabal v2-build             && \
    cabal v2-install --install-method=copy --installdir="$CRYPTOL_COMPILER_INSTALL_DIR"

################################################################################
# Stage: base-amd64 (base of runtime image when building for amd64)
################################################################################
# @note Having this stage is somewhat of a hack so that we can define
# different values for Z3_RELEASE_[ZIP/DIR] depending on ${TARGETARCH}.
# The actual value of ${TARGETARCH} might not match amd64; but in that case,
# this stage is simply ignored and not used below by the runtime stage.
################################################################################

# Image providing the base OS for the runtime image when amd64.
FROM --platform=${TARGETARCH} ubuntu:25.04 AS base-amd64

# Update installed packages from repository.
RUN apt-get update     && \
    apt-get upgrade -y && \
    apt-get clean

# We fetch Z3 version 4.15.1 (June 10, 2025) for x86_64 (amd64).

# Z3 release to be added to this image (June 10, 2025).
ARG Z3_RELEASE_ZIP="https://github.com/Z3Prover/z3/releases/download/z3-4.15.1/z3-4.15.1-x64-glibc-2.39.zip"

# Folder created by unzipping the above Z3 release.
ARG Z3_RELEASE_DIR="z3-4.15.1-x64-glibc-2.39"

################################################################################
# Stage: base-arm64 (base of runtime image when building for arm64)
################################################################################
# @note Having this stage is somewhat of a hack so that we can define
# different values for Z3_RELEASE_[ZIP/DIR] depending on ${TARGETARCH}.
# The actual value of ${TARGETARCH} might not match amd64; but in that case,
# this stage is simply ignored and not used below by the runtime stage.
################################################################################

# Image providing the base OS for the runtime image when arm64.
FROM --platform=${TARGETARCH} ubuntu:25.04 AS base-arm64

# Update installed packages from repository.
RUN apt-get update     && \
    apt-get upgrade -y && \
    apt-get clean

# We fetch Z3 version 4.15.1 (June 10, 2025) for aarch64 (amd64).

# Z3 release to be added to this image (June 10, 2025).
ARG Z3_RELEASE_ZIP="https://github.com/Z3Prover/z3/releases/download/z3-4.15.1/z3-4.15.1-arm64-glibc-2.34.zip"

# Folder created by unzipping the above Z3 release.
ARG Z3_RELEASE_DIR="z3-4.15.1-arm64-glibc-2.34"

################################################################################
# Stage: runtime (produces final `cryptol-compiler` runtime image)
################################################################################

# Runtime image providing cryptol-compiler, Z3 and (not) Rust.
FROM base-${TARGETARCH} AS runtime

# Author of the image (Frank Zeyda)
LABEL org.opencontainers.image.authors="Frank Zeyda <frank.zeyda@freeandfair.us>"

# Version of the packaged software (cryptol-compiler)
LABEL org.opencontainers.image.version="0.9.0.0"

# Name of the distributing entity, organization or individual.
LABEL org.opencontainers.image.vendor="Free & Fair, PBC"

# Human-readable title of the image (string)
LABEL org.opencontainers.image.title="Cryptol-to-Rust compiler binary"

# Human-readable description of the software packaged in the image (string)
LABEL org.opencontainers.image.description="Translates Cryptol specifications into executable Rust code; developed by Galois, Inc."

# Git tag of the cryptol-compiler release.
ARG CRYPTOL_COMPILER_TAG

# Installation directory for the cryptol-compiler binary.
ARG CRYPTOL_COMPILER_INSTALL_DIR

# Install additional prerequisites needed by runtime.
# @note build-essential is needed if including Rust
# (perhaps not all of it, see if we can prune down)
RUN apt-get install -y locales curl zip && \
    apt-get clean

# Set up environment for Unicode.
RUN echo "en_US.UTF-8 UTF-8" >> /etc/locale.gen
RUN locale-gen en_US.UTF-8
ENV LC_ALL="en_US.UTF-8"

# Install Z3 by downloading and extracting the release .zip.
RUN cd /opt                                              && \
    curl -q -s -S -L -o z3-release.zip "$Z3_RELEASE_ZIP" && \
    unzip z3-release.zip                                 && \
    rm z3-release.zip

# Add Z3 binaries to PATH.
ENV PATH="/opt/$Z3_RELEASE_DIR/bin:$PATH"

# Copy cryptol-compiler binary form build into runtime image.
COPY --from=build $CRYPTOL_COMPILER_INSTALL_DIR $CRYPTOL_COMPILER_INSTALL_DIR

# Add cryptol-compiler binary to PATH.
ENV PATH="/opt/cryptol-compiler-$CRYPTOL_COMPILER_TAG/bin:$PATH"

# Create a non-root user and run image under it.
RUN groupadd -g 1001 cryptol
RUN useradd -m -u 1001 -g 1001 cryptol
USER cryptol

# Set the default working directory.
WORKDIR /home/cryptol

# Install rustup for the `cryptol` user.
# We use the 1.80.0 toolchain as default as this is the one
# currently supported by `cryptol-compiler` (see README.md).
# @see https://www.rust-lang.org/tools/install
# RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | \
#     sh -s -- -y --default-toolchain 1.80.0

# Default command to run when the container is started
CMD ["/bin/bash"]
