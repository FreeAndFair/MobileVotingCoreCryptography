############################################################################
# Dockerfile for the Free&Fair E2E-VIV DE/PLE Docker image (de-ple-e2eviv) #
############################################################################
# Use Ubuntu 22.04 (not newer) for libncurses5, required by claferIG.
FROM --platform=linux/amd64 ubuntu:22.04

# Clafer tools version and download URL
# Obtained from: https://gsd.uwaterloo.ca/clafer-tools-binary-distributions
ARG CLAFER_TOOLS_VER="clafer-tools-0.4.5"
ARG CLAFER_TOOLS_ZIP="$CLAFER_TOOLS_VER-linux-x86_64.zip"
ARG CLAFER_TOOLS_URL="https://gsd.uwaterloo.ca/clafer-tools-bin/$CLAFER_TOOLS_ZIP"

# Update Ubuntu packages and install prerequisites.
RUN apt-get clean && \
    apt-get update && \
    apt-get upgrade -y && \
    apt-get upgrade -y wget unzip git pip npm openjdk-17-jre libncurses5 && \
    apt-get clean

# Install jsons library from PyPi.
RUN pip install jsons

# Copy Lando installation files.
ADD resources/lando /opt/lando

# Install Clafer tools by downloading binary archive.
RUN mkdir /opt/clafer && \
    cd /opt/clafer && \
    wget $CLAFER_TOOLS_URL && \
    unzip $CLAFER_TOOLS_ZIP && \
    rm $CLAFER_TOOLS_ZIP

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
RUN mkdir -p /home/clafertools040 && \
    ln -s /opt/clafer/$CLAFER_TOOLS_VER /home/clafertools040/bin

# Copy start-up script for starting all three Clafer IDEs.
COPY resources/startup.sh /root/

# Include lando and clafer CLI tools in PATH.
ENV PATH="/opt/clafer/$CLAFER_TOOLS_VER:$PATH"
ENV PATH="/opt/lando/bin:$PATH"

# Set the default working directory.
WORKDIR /root

# Automatically start Clafer IDEs.
ENTRYPOINT ["/root/startup.sh"]

# Passed to and executed by startup.sh.
CMD ["/bin/bash"]
