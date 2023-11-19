# Development Environment
## Getting Started with Vagrant

Vagrant is an open-source software product for building and maintaining portable virtual software development environments. It can be used on various operating systems like macOS, Windows, and Linux.

### Prerequisites

- Install [VirtualBox](https://www.virtualbox.org/)
- Install [Vagrant](https://www.vagrantup.com/downloads)

### Basic Vagrant Commands

#### Adding a Box

A "box" is a package format for Vagrant environments. To add a box from Vagrant Cloud:

```shell
vagrant box add ubuntu/focal64
```
Initializing a Project
To initialize a new Vagrant project with a Vagrantfile:

```shell
vagrant init ubuntu/focal64
```
Starting a Vagrant Box
To start and provision the Vagrant environment:

```shell
vagrant up
```
SSH into the Box
To connect to your box via SSH:

```shell
vagrant ssh
```
Stopping a Vagrant Box
To suspend your virtual machine, saving its current state:

```shell
vagrant suspend
```
To shut down the virtual machine:

```shell
vagrant halt
```
### Destroying a Vagrant Box
To completely remove the virtual machine:

```shell
vagrant destroy
```
## Synced Folders
By default, Vagrant will share your project directory (where the Vagrantfile is located) to the /vagrant directory in your virtual machine.

## Networking
You can configure network settings to access your Vagrant machine through your host machine.

## Provisioning
Vagrant can automatically install software, alter configurations, and more on the machine upon vagrant up or vagrant reload.

