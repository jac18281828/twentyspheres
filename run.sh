#!/usr/bin/env bash

VERSION=$(date +%m%d%y)

docker build . -t twenty:${VERSION} && \
	docker run --rm -i -t twenty:${VERSION}
