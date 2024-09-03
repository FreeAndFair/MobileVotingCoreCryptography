#! /bin/bash
set -e # exit immediately upon error(s)

# Name of the docker image to run
IMAGE="de-ple-e2eviv"

# Platform
PLATFORM="--platform linux/amd64"

# Port mapping to expose Clafer IDE tools
PORT_OPTS="-p 8092:8092 -p 8093:8093 -p 8094:8094"

# Working directory in the container
WORKDIR="/work"

# Volume mapping. We map the current directory.
VOLUME="$PWD:$WORKDIR"

# Print an informative message about volume mapping.
echo "Mapping current folder to /work inside the container."

# Run container interactively and automatically destroy it when exiting.
docker run -it --rm $PORT_OPTS -v "$VOLUME" -w "$WORKDIR" $IMAGE
