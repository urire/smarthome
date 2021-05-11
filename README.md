# Smarthome

- The smart home hub communicates with third-party devices (sensors and controllers) threw Agents (using shared objects
  and Factory pattern).

- Sensors are devices that gather information from the environment and sending it to the hub.

- Controllers are devices that receive information from the hub, and react accordingly.

- The hub is multi-threaded and ensures that the events will be sent to the controllers in the exact order which they
  arrived from the sensors. Each controller can respond to one event of each type simultaneously.

The project developed in C++ 03, some tools were written as new classes (shared_ptr, thread, thread_pool...)
