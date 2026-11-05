FROM ubuntu:24.04 AS builder
RUN apt-get update && apt-get install -y \
    g++ cmake libgtest-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN cmake -S . -B build-docker -DCMAKE_BUILD_TYPE=Release
RUN cmake --build build-docker -j2
RUN ctest --test-dir build-docker --output-on-failure

FROM ubuntu:24.04

RUN apt-get update && apt-get install -y libstdc++6 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY --from=builder /app/build-docker/matrix_calculator .

CMD ["./matrix_calculator"]