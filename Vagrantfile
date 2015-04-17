# -*- mode: ruby -*-
# vi: set ft=ruby :

# Vagrantfile API/syntax version. Don't touch unless you know what you're doing!
VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  config.vm.define "blockbuster" do |blockbuster|
    blockbuster.vm.box = "ubuntu/trusty64"
    blockbuster.vm.box_url = "https://cloud-images.ubuntu.com/vagrant/trusty/current/trusty-server-cloudimg-amd64-vagrant-disk1.box"
    blockbuster.vm.provider :virtualbox do |vb|
      vb.name = "blockbuster"
    end

    blockbuster.vm.provision "shell",
      inline: "apt-get install --yes --quiet qt5-qmake qtdeclarative5-dev libbox2d-dev qt5-default g++ gdb libgtest-dev"

    blockbuster.ssh.forward_x11 = true
  end

end
