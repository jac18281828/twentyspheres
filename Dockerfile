ARG VERSION=bullseye-slim

FROM debian:${VERSION} 

RUN export DEBIAN_FRONTEND=noninteractive && \
    apt update && \
    apt -y install build-essential gcc-10 cmake \
        gdb python3 libjpeg-dev

# build project
ARG PROJECT=twentysphr
WORKDIR /workspaces/${PROJECT}

COPY include include/
COPY src src/
COPY test test/
COPY CMakeLists.txt .    

ARG BUILD=build
ARG TYPE=DEBUG

#build
ENV MAKEFLAGS=-j14
RUN cmake -H. -B${BUILD} -DPROJECT_NAME=${PROJECT} -DCMAKE_BUILD_TYPE=${TYPE} -DCMAKE_VERBOSE_MAKEFILE=on "-GUnix Makefiles"
RUN cmake --build ${BUILD} --verbose --config ${TYPE}
ENV CTEST_OUTPUT_ON_FAILURE=1

RUN (cd ${BUILD} && ctest)
ENV PROJECT_NAME=${PROJECT}
CMD build/${PROJECT_NAME} twenty.jpg
