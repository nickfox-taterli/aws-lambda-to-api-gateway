# AWS C++ Lambda & API Gateway

We'll build a Lambda function that can be used as an API Gateway proxy to echo your input parameters from HTTP GET request.

That being said, the instructions below should work on any Linux distribution.

## Prerequisites
1. CMake (version 3.15 or later)
2. git
3. Make or Ninja
4. zip
5. libcurl-devel

## Build the AWS Lambda SDK
In a terminal, run the following commands:
```bash
$ git clone https://github.com/awslabs/aws-lambda-cpp.git
$ cd aws-lambda-cpp
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Release
$ make && make install
```

## Build the AWS C++ SDK
Start by building the SDK from source.
```bash
$ mkdir ~/install
$ git clone https://github.com/aws/aws-sdk-cpp.git
$ cd aws-sdk-cpp
$ mkdir build
$ cd build
$ cmake .. -DBUILD_ONLY="core" \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_SHARED_LIBS=OFF \
  -DENABLE_UNITY_BUILD=ON \
  -DCUSTOM_MEMORY_MANAGEMENT=OFF \
  -DENABLE_UNITY_BUILD=ON

$ make -j 4
$ sudo make install
```

## Build the Runtime
Now let's build the C++ Lambda runtime, so in a separate directory clone this repository and follow these steps:

```bash
$ git clone https://github.com/awslabs/aws-lambda-cpp-runtime.git
$ cd aws-lambda-cpp-runtime
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_SHARED_LIBS=OFF \
$ make
$ sudo make install
```

## Build the application
The last step is to build the Lambda function in `main.cpp` and run the packaging command as follows:

```bash
$ git clone https://github.com/nickfox-taterli/aws-lambda-to-api-gateway
$ cd aws-lambda-to-api-gateway
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=~/install
$ make
$ make aws-lambda-package-demo
```

You should now have a zip file called `demo.zip`. 

## First Commit Your Code
Make sure you attach the appropriate policies and/or permissions for any other AWS services that you plan on using.

Then,create the Lambda function:

```
$ aws lambda create-function --function-name demo \
--role <specify role arn here> \
--runtime provided --timeout 15 --memory-size 128 \
--handler demo --zip-file fileb://demo.zip
```

## Update Code
Make sure you attach the appropriate policies and/or permissions for any other AWS services that you plan on using.

Then,create the Lambda function:

```
$ aws lambda update-function-code --function-name demo \
--zip-file fileb://demo.zip
```