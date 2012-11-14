package com.universalremote;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.nio.ByteBuffer;

public class CommandSender {
	
	private DatagramSocket datagramSocket;
	private int port;
	private String ipAddress;
	
	public CommandSender() throws SocketException {
		this.port = 56000;
		this.ipAddress = "192.168.1.9";
		this.datagramSocket = new DatagramSocket();
	}
	
	public CommandSender(String ipAddress, int port) throws SocketException {
		this.port = port;
		this.ipAddress = ipAddress;
		this.datagramSocket = new DatagramSocket();	
	}
	
	public boolean sendCommand(String cmdBuffer) {
		try {
			byte[] buffer = cmdBuffer.getBytes();
			datagramSocket.send(new DatagramPacket(buffer, buffer.length, InetAddress.getByName(ipAddress), port));
			return true;
		} catch (UnknownHostException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return false;
	}
	

}
