#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdint.h>
#include <string.h>
#include <memory.h>
#include <iostream>

using namespace std;

struct linux_dirent {
	uint64_t d_ino;
	int64_t d_off;
	unsigned short d_reclen;
	unsigned char d_type;
	char d_name[0];
};

ostream& operator<<(ostream& os, const linux_dirent& d) {
	os << "size[" << sizeof(d) << "]\n"
		<< "d_ino[" << d.d_ino << "]\n" 
		<< "d_off[" << d.d_off << "]\n"
		<< "d_reclen[" << d.d_reclen << "]\n"
		<< "d_type[" << (int)d.d_type << "]\n" 
		<< "d_name[" << d.d_name << "]";
}

int main(int argc, char* argv[]) {
	const char* dir_path = "/home/arma";
	if (argc > 1) {
		dir_path = argv[1];
	}
	int fd = open(dir_path, O_RDONLY | O_DIRECTORY);
	if (fd < 0) {
		printf("failed to open %s, error: %s", dir_path, strerror(errno));
		exit(-1);
	}	
	unsigned char buf[1024];
	memset(buf, 0, sizeof(buf));
	int r = syscall(__NR_getdents64, fd, buf, sizeof(buf));
	if (r == 0) {
		cout << "empty dir" << endl;
		return 0;
	}

	if (r == -1) {
		cout << "__NR_getdents64 failed, error: " << strerror(errno) << endl;
		exit(-1);
	}

	int size = r;
	int offset = 0;

	while (offset < size) {
		linux_dirent* d = reinterpret_cast<linux_dirent*>(buf + offset);
		offset += d->d_reclen;
		cout << *d << "\n--------------------" << endl;
	}
	return 0;
}
