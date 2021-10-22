#!/usr/bin/env bash

VERSION=$(date +%s)

docker build . -t twenty:${VERSION} && \
	docker run --rm -i -t twenty:${VERSION}
