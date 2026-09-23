# Tuya System Daemon for RutOS

## Overview

This project contains the source code of a RutOS daemon responsible for collecting router information through ubus and sending it to the Tuya IoT Cloud.

## Features

- Collects router information using ubus.
- Sends collected data to the Tuya IoT Cloud.
- Provides syslog logging.
- Runs as a background daemon service.

## Components

- `system_info` - router information collection.
- `tuya-agent` - Tuya Cloud communication layer.
