#!/usr/bin/env php
<?php
/**
 * Open a listening socket on localhost port 61613.
 */

$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
socket_bind($socket, '127.0.0.1', '61613');
socket_listen($socket);

do {
    $socket_instance = socket_accept($socket);
    $end = FALSE;
    $msg = '';
    do {
      // Read until NUL is sent
      $buffer = socket_read($socket_instance, 2048);
      $pos = strpos($buffer, 0x00);
      if ($pos !== FALSE) {
        error_log("NULL detected at pos $pos");
        $buffer = substr($buffer, 0, $pos);
        $end = TRUE;
      }
      $msg .= $buffer;
    } while ($end == FALSE);
    // Replay the message.
    socket_write($socket_instance, "You said: " . $msg);
    socket_close($socket_instance);
} while (true);

