make
sudo cp DocServer.service /lib/systemd/system
sudo systemctl daemon-reload
sudo systemctl start DocServer.service
sudo systemctl enable DocServer.service
sudo systemctl status DocServer.service