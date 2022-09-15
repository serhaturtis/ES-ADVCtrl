<div id="top"></div>

<br />
<div align="center">

<h3 align="center">ADVCtrl</h3>

  <p align="center">
    A small tool to reconfigure ADV7x8x devices from IIC bus
  </p>
</div>

<!-- WHAT -->
## What?

This is a small quick tool to configure ADV7x8x devices, (although i used it for adv7280 only, and the others are not implemented).

## Why?

Because i needed to reconfigure/test after linux kernel module probed the device.

## How?

Usage: advctrli2c -a -i <input_type> -c <input_channel> input types: 0: PAL, 1: NTSC input channels: CVBS: 0-7, SVIDEO: 8-11
