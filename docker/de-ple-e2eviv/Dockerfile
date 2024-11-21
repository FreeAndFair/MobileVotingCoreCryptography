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
FROM --platform=linux/amd64 ubuntu:22.04 AS de-ple-e2eviv

# Clafer tools version and download URL
# Obtained from: https://gsd.uwaterloo.ca/clafer-tools-binary-distributions
ARG CLAFER_TOOLS_VER="clafer-tools-0.4.5"
ARG CLAFER_TOOLS_ZIP="$CLAFER_TOOLS_VER-linux-x86_64.zip"
ARG CLAFER_TOOLS_URL="https://gsd.uwaterloo.ca/clafer-tools-bin/$CLAFER_TOOLS_ZIP"

# Update Ubuntu packages and install prerequisites.
RUN apt-get clean && \
    apt-get update && \
    apt-get upgrade -y && \
    apt-get upgrade -y build-essential wget unzip git pip npm openjdk-17-jre plantuml libncurses5 locales && \
    apt-get clean

# Install "jsons" library from PyPI.
RUN pip install jsons

# Copy Lando installation files.
ADD resources/lando /opt/lando

# Install Clafer tools by downloading binary archive.
RUN mkdir /opt/clafer && \
    cd /opt/clafer && \
    wget $CLAFER_TOOLS_URL && \
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
RUN mkdir -p /home/clafertools040 && \
    ln -s /opt/clafer/$CLAFER_TOOLS_VER /home/clafertools040/bin

# Install "lark" library from PyPI, necessary for choco_to_json.py.
RUN pip install lark

# Set up environment for Unicode.
RUN echo "en_US.UTF-8 UTF-8" >> /etc/locale.gen
RUN locale-gen en_US.UTF-8
ENV LC_ALL="en_US.UTF-8"

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
