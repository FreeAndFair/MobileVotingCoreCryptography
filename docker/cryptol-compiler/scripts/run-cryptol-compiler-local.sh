#!/bin/bash
set -e # exit immediately upon error(s)

# Name of the docker image to run
IMAGE="cryptol-compiler"

# Version of the docker image to run
TAG="0.9.0.0"

# Platform
PLATFORM1="--platform linux/amd64"
PLATFORM2="--platform linux/arm64"
PLATFORM="" # let OS choose

# Port mapping to expose Clafer IDE tools
PORT_OPTS=""

# Working directory in the container
WORKDIR="/work"

# Volume mapping. We map the current directory.
VOLUME="$PWD:$WORKDIR"

# Print an informative message about volume mapping.
echo "Mapping current folder to /work inside the container."

# Run container interactively and automatically destroy it when exiting.
docker run -it --rm $PLATFORM $PORT_OPTS -v "$VOLUME" -w "$WORKDIR" $IMAGE:$TAG
