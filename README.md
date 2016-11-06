ftpBNC can either operate with a normal text file based config,
or an embedded encrypted config.

On ubuntu this is needed -> apt install build-essential

* Normal text file config:

  1. Compile the bouncer by running 'make'.
  2. Edit ftpBNC.conf to suit your needs.
  3. Run the bouncer './ftpBNC ftpBNC.conf'.
  4. Added entry to crontab to start at boot:

    @reboot /home/user/ftpBNC/ftpBNC /home/user/ftpBNC/ftpBNC.conf >/dev/null
  
* Embedded encrypted config:

  1. Compile and run the conf editor tool by running 'make conf'.
  2. Compile the bouncer by running 'make'.
  3. Run the bouncer './ftpBNC' (not ftpBNC.conf argument).

  Note: Crontab is unsupported with encrypted config.

------------------------------------------------------- --- -> >
