############################################################################
# Dockerfile for the Free&Fair E2E-VIV DE/PLE Docker image (de-ple-e2eviv) #
############################################################################

# First, build the current Chocosolver - no need for amd64 here because
# we're just doing a Java build with Maven.

FROM ubuntu:22.04 AS chocosolver

RUN apt-get clean && \
    apt-get update && \
    apt-get upgrade -y && \
    apt-get upgrade -y build-essential git openjdk-17-jre maven && \
    apt-get clean

RUN cd /tmp && \
    git clone https://github.com/GaloisInc/chocosolver.git && \
    cd chocosolver && \
    mvn install && \
    make install to=/opt/chocosolver

# /opt/chocosolver/chocosolver.jar should now exist in the "chocosolver" image.

# Then, build the actual DE/PLE image.
# Use Ubuntu 22.04 (not newer) for libncurses5, required by claferIG.
# The use of TARGETARCH here avoids a Docker warning about selecting a
# static build architecture.
FROM --platform=${TARGETARCH} ubuntu:22.04 AS de-ple-e2eviv

# Clafer tools version and download URL
# Obtained from: https://gsd.uwaterloo.ca/clafer-tools-binary-distributions
ARG CLAFER_TOOLS_VER="clafer-tools-0.4.5"
ARG CLAFER_TOOLS_ZIP="$CLAFER_TOOLS_VER-linux-x86_64.zip"
ARG CLAFER_TOOLS_URL="https://gsd.uwaterloo.ca/clafer-tools-bin/$CLAFER_TOOLS_ZIP"
ARG CLAFER_TOOLS_SHA256SUM="da133fd2d0c1fe210d7562e0576ca89c236efac15cab85cbc11d2b9adb5833e9  $CLAFER_TOOLS_ZIP"

# Update Ubuntu packages and install prerequisites.
RUN apt-get clean && \
    apt-get update && \
    apt-get upgrade -y && \
    apt-get upgrade -y build-essential wget unzip git python3-pip npm openjdk-17-jre plantuml libncurses5 locales && \
    apt-get clean

# Set up environment for Unicode.
RUN echo "en_US.UTF-8 UTF-8" >> /etc/locale.gen
RUN locale-gen en_US.UTF-8
ENV LC_ALL="en_US.UTF-8"

# Copy Lando installation files.
ADD resources/lando /opt/lando

# Create and run as non-root user
RUN groupadd -g 1001 ple
RUN useradd -m -u 1001 -g 1001 ple
RUN mkdir -p /opt/clafer
RUN chgrp -R ple /opt/clafer /opt/lando
RUN chmod -R ug+rwX /opt/clafer /opt/lando
USER ple

# Install "jsons" library from PyPI.
RUN pip install jsons

# Install Clafer tools by downloading binary archive.
# We don't check the SSL cert because it's broken, but we do
# check the SHA256 checksum of the downloaded archive. In the
# future we may move this archive to a Free & Fair site.
RUN cd /opt/clafer && \
    wget --no-check-certificate $CLAFER_TOOLS_URL && \
    echo ${CLAFER_TOOLS_SHA256SUM} | sha256sum --check && \
    unzip $CLAFER_TOOLS_ZIP && \
    rm $CLAFER_TOOLS_ZIP

# Copy freshly built chocosolver.jar from the chocosolver image.
COPY --from=chocosolver /opt/chocosolver/chocosolver.jar /opt/clafer/$CLAFER_TOOLS_VER/chocosolver.jar
ADD resources/chocosolver /opt/clafer/$CLAFER_TOOLS_VER/chocosolver

# Install ClaferIDE, master branch (port 8094).
RUN cd /opt/clafer && \
    git clone https://github.com/gsdlab/ClaferIDE.git && \
    cd ClaferIDE && \
    git submodule init && \
    git submodule update && \
    cd Server && \
    npm install

# Install ClaferConfigurator, master branch (port 8093).
RUN cd /opt/clafer && \
    git clone https://github.com/gsdlab/ClaferConfigurator.git && \
    cd ClaferConfigurator && \
    git submodule init && \
    git submodule update && \
    cd Server && \
    npm install

# Install ClaferMooVisualizer, develop branch (port 8092).
RUN cd /opt/clafer && \
    git clone https://github.com/gsdlab/ClaferMooVisualizer.git && \
    cd ClaferMooVisualizer && \
    git submodule init && \
    git submodule update && \
    git submodule foreach git checkout develop && \
    cd Server && \
    npm install

# Clafer IDEs expect the clafer tools to be in /home/clafertools040/
USER root
RUN mkdir -p /home/clafertools040 && \
    ln -s /opt/clafer/$CLAFER_TOOLS_VER /home/clafertools040/bin && \
    chown -R ple:ple /home/clafertools040
USER ple

# Install "lark" library from PyPI, necessary for choco_to_json.py.
RUN pip install lark

# Copy start-up script for starting all three Clafer IDEs.
COPY resources/startup.sh /home/ple

# Create bash alias for Clafer in root's home directory, to
# ensure "clafer -v" can find the jar files.
RUN echo "alias clafer='clafer --tooldir=/opt/clafer/${CLAFER_TOOLS_VER}'" >> /home/ple/.bash_aliases

# Include lando and clafer CLI tools in PATH.
ENV PATH="/opt/clafer/$CLAFER_TOOLS_VER:$PATH"
ENV PATH="/opt/lando/bin:$PATH"

# Set the default working directory.
WORKDIR /home/ple

# Automatically start Clafer IDEs.
ENTRYPOINT ["/home/ple/startup.sh"]

# Passed to and executed by startup.sh.
CMD ["/bin/bash"]
