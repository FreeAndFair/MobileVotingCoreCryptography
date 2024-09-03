#! /usr/bin/env bash
set -e # exit immediately upon error(s)

# ANSI escape sequences for fonts and colors
ANSI_NORM="\e[0m"
ANSI_BOLD="\e[1m"
ANSI_BLACK="\e[30m"
ANSI_RED="\e[31m"
ANSI_GREEN="\e[32m"
ANSI_YELLOW="\e[33m"
ANSI_BLUE="\e[34m"
ANSI_MAGENTA="\e[35m"
ANSI_CYAN="\e[36m"
ANSI_GRAY="\e[37m"

# ClaferIDE is running on port 8094 (must be exposed)
echo -e "Starting ${ANSI_BOLD}ClaferIDE${ANSI_NORM} on port 8094 ..."
cd /opt/clafer/ClaferIDE/Server &&
node ClaferIDE.js > /root/ClaferIDE.log 2>&1 &

# ClaferConfigurator is running on port 8093 (must be exposed)
echo -e "Starting ${ANSI_BOLD}ClaferConfigurator${ANSI_NORM}on port 8093 ..."
cd /opt/clafer/ClaferConfigurator/Server &&
node ClaferConfigurator.js > /root/ClaferConfigurator.log 2>&1 &

# ClaferMooVisualizer is running on port 8092 (must be exposed)
echo -e "Starting ${ANSI_BOLD}ClaferMooVisualizer${ANSI_NORM} on port 8092 ..."
cd /opt/clafer/ClaferMooVisualizer/Server &&
node ClaferMooVisualizer.js > /root/ClaferMooVisualizer.log 2>&1 &

# Diplay information where .log files for the above can be found.
echo "See /root/{ClaferIDE,ClaferConfigurator,ClaferMooVisualizer}.log for errors"
echo

# Display information on how to access the IDEs from localhost.
echo "To access the above tools use the local URLs:"
echo -e "➤ ${ANSI_GREEN}localhost:8092${ANSI_NORM} for ClaferMooVisualizer"
echo -e "➤ ${ANSI_GREEN}localhost:8093${ANSI_NORM} for ClaferConfigurator"
echo -e "➤ ${ANSI_GREEN}localhost:8094${ANSI_NORM} for ClaferIDE"
echo

# Display information on how to run DE/PLE command line tools.
echo "To use the Lando and Clafer tools from the command line type:"
echo -e "➤ ${ANSI_CYAN}lando${ANSI_NORM}    for the Lando parser (generates JSON)"
echo -e "➤ ${ANSI_CYAN}clafer${ANSI_NORM}   for the Clafer parser"
echo -e "➤ ${ANSI_CYAN}claferIG${ANSI_NORM} for the Clafer instance generator"
echo -e "${ANSI_GRAY}All tool installations can be found under /opt/{lando,clafer}.${ANSI_NORM}"
echo

# Display information on how to exit the container.
echo -e "Type ${ANSI_RED}exit${ANSI_NORM} to exit and automatically destroy the container."

# Execute whatever command is passed to the script.
eval "$*"
