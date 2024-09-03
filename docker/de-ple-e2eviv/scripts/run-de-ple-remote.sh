#! /bin/bash
set -e # exit immediately upon error(s)

# URL of the docker repository
REPOSITORY="registry-1.docker.io"

# Name of the organization
ORGANIZATION="freeandfair"

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

# Log into dockerhub if the image is not present.
if [ -z "$(docker images -q $ORGANIZATION/$IMAGE 2> /dev/null)" ]; then
  echo "Logging into docker repository: $REPOSITORY"
  docker login $REPOSITORY
fi

# Print an informative message about volume mapping.
echo "Mapping current folder to /work inside the container."

# Run container interactively and automatically destroy it when exiting.
docker run -it --rm $PORT_OPTS -v "$VOLUME" -w "$WORKDIR" $ORGANIZATION/$IMAGE:latest
