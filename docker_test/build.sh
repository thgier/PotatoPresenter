#!/bin/bash

set -xe

sudo docker build -t ubuntu .
containerID=$(sudo docker run -dti --device /dev/fuse --cap-add SYS_ADMIN ubuntu /bin/bash)

function finish {
    sudo docker stop $containerID
    sudo docker rm $containerID
}
trap finish EXIT

sudo docker cp build_appimage.sh $containerID:/
sudo docker exec $containerID /build_appimage.sh $1

sudo docker cp $containerID:/potatoPresenter.AppImage PotatoPresenter-$(git describe).AppImage

