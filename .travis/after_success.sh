#!/bin/bash

set -e

# Travis Webhook

wget https://raw.githubusercontent.com/DiscordHooks/travis-ci-discord-webhook/master/send.sh
chmod +x send.sh
./send.sh success ${WEBHOOK_URL}

# Deployment

#export VERSION=$(git describe --tags)
#if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
#  wget -c -nv "https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage"
#  chmod a+x linuxdeployqt-continuous-x86_64.AppImage
#  ./linuxdeployqt-continuous-x86_64.AppImage ${PROJECT_NAME}/usr/share/applications/*.desktop -appimage -no-plugins -no-strip -verbose=2
#  export DEPLOYFILE=${PROJECT_NAME}-${VERSION}-x86_64.AppImage
#elif [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
#  macdeployqt ${PROJECT_TARGET}.app -dmg -verbose=2
#  mv ./${PROJECT_TARGET}.dmg ./${PROJECT_NAME}-${VERSION}.dmg
#  export DEPLOYFILE=${PROJECT_NAME}-${VERSION}.dmg
#fi
