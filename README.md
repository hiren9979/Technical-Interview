import paramiko
import time

router_ip = "192.168.56.101"  # Router management IP address
username = "admin"            # Replace with your router username
password = "password"         # Replace with your router password

config_commands = [
    "configure terminal",
    # Configure Loopback interface
    "interface Loopback0",
    "ip address 10.0.0.1 255.255.255.255",  # Loopback IP address
    "no shutdown",
    "exit",
    # Configure GigabitEthernet1
    "interface GigabitEthernet1",
    "ip address 192.168.56.101 255.255.255.0",  # GigabitEthernet1 IP
    "no shutdown",
    "exit",
    # Configure OSPF
    "router ospf 1",
    "network 192.168.56.0 0.0.0.255 area 0",  # Advertise GigabitEthernet1 network
    "network 10.0.0.0 0.0.0.255 area 0",      # Advertise Loopback network
    "end",
    "write memory"
]

def configure_router(router_ip, username, password, commands):
    try:
        # Establish SSH connection
        ssh = paramiko.SSHClient()
        ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        ssh.connect(router_ip, username=username, password=password)
        
        print("SSH connection established...")
        
        # Start an interactive shell session
        remote_conn = ssh.invoke_shell()
        output = ""
        
        # Wait for the shell to be ready
        time.sleep(2)
        
        # Clear initial buffer
        if remote_conn.recv_ready():
            output = remote_conn.recv(65535).decode("utf-8")
            print(output)

        # Enter enable mode
        print("Entering enable mode...")
        remote_conn.send("enable\n")
        time.sleep(1)
        
        if remote_conn.recv_ready():
            output = remote_conn.recv(65535).decode("utf-8")
            print(output)
            
        remote_conn.send(f"{password}\n")
        time.sleep(1)
        
        # Send configuration commands
        print("Sending configuration commands...")
        for command in commands:
            remote_conn.send(command + "\n")
            time.sleep(2)  # Increased delay to ensure command completion
            
            while remote_conn.recv_ready():
                output += remote_conn.recv(65535).decode("utf-8")
                print(f"Command output: {output}")
                
        # Final wait to ensure all output is received
        time.sleep(2)
        while remote_conn.recv_ready():
            output += remote_conn.recv(65535).decode("utf-8")
        
        print("Configuration completed.")
        print("Final output:", output)
        
        # Close connections
        remote_conn.close()
        ssh.close()
        
    except Exception as e:
        print(f"An error occurred: {e}")
        if 'ssh' in locals():
            ssh.close()

configure_router(router_ip, username, password, config_commands)
