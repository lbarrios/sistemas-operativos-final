#include <iostream>
#include <assert.h>

#include "hdd.h"
#include "mbr.h"
#include "pentry.h"
#include "ext2fs.h"


using namespace std;

void test_file_system(Ext2FS * fs){
	cout << "=== Filesystem Superblock ===" << endl;
	cout << *(fs->superblock()) << endl;

	//Verifico que la informacion de la cantidad de bloques sea la esperada
	assert(fs->superblock()->blocks_count == 102400);
}

void test_hdd(HDD * hdd){
	unsigned char buffer[SECTOR_SIZE];
	hdd->read(0, buffer);
	MBR mbr(buffer);
	const PartitionEntry & pentry = mbr[1];
	cout << "=== Partition Data ===" << endl;
	cout << pentry << endl << endl;

	//Verifico que la LBA empiece donde se espera
	assert(pentry.start_lba() == 4096);
}

void test_block_groups(Ext2FS * fs){
	cout << "=== Block Groups Data ===" << endl;
	unsigned int block_groups = fs->block_groups();
	for(unsigned int i = 0; i < block_groups; i++)
	{
		cout << *(fs->block_group(i)) << endl;
	}
	Ext2FSBlockGroupDescriptor block_group = *(fs->block_group(1));

	//Verifico que el block group 1 tenga la información correcta
	assert(block_group.block_bitmap == 8195);
}

int main(int argc, char ** argv)
{
	HDD hdd(argv[1]);

	test_hdd(&hdd);

	Ext2FS * fs = new Ext2FS(hdd, 1);

	test_file_system(fs);

	test_block_groups(fs);
	
	Ext2FSInode * i = fs->load_inode(23668);
	cout << *i << endl;

	i =  fs->load_inode(23718);
	cout << *i << endl;


	unsigned char buf2[14017];
	//buf2[14001] = 'a';
	fd_t file = fs->open("/grupos/g1/nota.txt","r");
	

	fs->seek(file, 13999);
	unsigned char buf[100];
	fs->read(file, (unsigned char*)buf, 17);
	buf[17]='\0';
	
	//fs->read(file, (unsigned char*)buf2, 14017);
	//buf2[14017]='\0';
	std::cout << "buf=" << buf << std::endl;

	return 0;
}