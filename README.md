# DK-Lockbox
_The Lockbox_ is a customizable MIDI controller compatible with any computer music software. It features an interchangeable set of 4 knobs and 3 analog joysticks to use in any arrangement.

![Lockbox MIDI Controller](/images/dk-lockbox_front.jpg)
![Lockbox MIDI Controller](/images/dk-lockbox_parts.jpg)

## About
This project is one of my more experimental high-quality MIDI controllers. It is available in my 
[Etsy Store: Circuits & Sawdust](https://www.etsy.com/listing/594208433/lockbox-customizable-midi-controller-box).

## How it works
This is a [Teensy LC](https://www.pjrc.com/teensy/) based USB MIDI controller with my usual smoothing algorithms to provide quality MIDI signals. It is programmed within Arduino, and extended by my own C++ classes to manage the knob values and value scaling across my collection of MIDI projects.

Each controller module is pinned in place by thumbtacks on a cork mat, and each control module can be switched out for another. A warm white LED strip in the top of the lid illuminates the controller.
