# Tuya Router Packages

## Overview

This repository contains OpenWRT/RutOS packages required for Tuya IoT Cloud integration.

## Packages

### tuya_iot_core
Provides the Tuya SDK used for communication with the Tuya IoT Cloud.

### tuya_daemon
Daemon service that collects router information and publishes it to the Tuya IoT Cloud.

### vuci-app-tuya-api
VuCI API package used to configure and control the Tuya daemon.

## Features

- Automatic Tuya SDK download during build.
- Router information collection through ubus.
- Cloud communication with Tuya IoT platform.
- Syslog support (`logread`).
- VuCI API integration.
