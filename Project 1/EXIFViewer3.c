// AquiatanEXIFview.c

# include <stdio.h>
# include <stdlib.h>
# include <string.h>


struct picHeader
{
	// 2 for file marker start
	// 2 for APP1 marker
	// 2 for length of APP1 block
	// 4 for EXIF
	// 2 for Nul
	// 2 for Endian
	// 2 for version number
	// 4 for offset to start of EXIF to start of TIFF
	// 10 + 10 = 20
	
	//picInfo = char[20];
	// that is one approach but
	// it'll be easier on me to just have a bunch of vars
	// from the skeleton code, there was usage of a lot of
	// unsigned ints, so I'm going to use that unless
	// I know for a fact it's going to be some sort of
	// character array, which makes everything
	// besides EXIF, Endianness, and maybe offset unsigned shorts
	// *offset cannot be a short since it makes no sense
	unsigned short fileStartMarker;
	unsigned short appMarker;
	unsigned short appLength;
	char exifString[4];
	unsigned short nulTerm;
	char endianness[2];
	unsigned short versionNum; // PLANNED for this to be int
	// as we knew it was 42
	// but then offset becomes 24 so I changed it to short
	unsigned int offset;
	
};

struct TIFFtag
{
	// 2 for tag ID
	// 2 for data type
	// 4 for data itmes
	// 4 for offset
	// 4*3 = 12
	// 12 char array
	// no need for individual fields since this stuff goes over like once
	//tiffInfo = char[12];
	unsigned short tagID;
	unsigned short dataType;
	unsigned int itemNum; // number of data numbers
	unsigned int TIFFoffset; // to differentiate from other offset
	
};










int main(int argc, char **argv)
{
	//FILE *picture;
	
	FILE * picture;
	struct picHeader header;
	struct TIFFtag pictag;
	static int offset = 0;
	
	// we're processing .jpg's only so should check on that
	// but we also want to make sure that the command went in properly
	// so first
	// let's catch it if there isn't 2 arguments
	// as ./Exif is 1
	// and the image.jpg is 2
	if(argc != 2)
	{
		printf("Incorrect usage of the program.\n");
		printf("The Correct Usage is:\n");
		printf("./exifview [imagefilename].jpg\n");
		return 1;
	}
	
	// okay now let's quickly check the file
	// it should contain .jpg
	char *fileChecker = NULL;
	fileChecker = strstr(argv[1], ".jpg");
	if(fileChecker == NULL)
	{
		printf("Not a jpeg\n");
		return 1;
	}
	
	
	//printf("Uhhh.\n"); // debugging line, ignore
	// now we have checked that we have
	// a) proper amount of inputs
	// b) picture is in fact, in jpg format
	// now it is time for us to open up the file!
	
	picture = fopen(argv[1], "rb"); // read only as we only need to read, plus binary style
	// now let's read stuff in
	// we're going to read it into our
	// struct, as it's been formatted
	// to mimic the structure of a jpeg file!
	fread(&header, sizeof(header), 1, picture);
	// or:
	// output to header
	// read the size of our struct's bytes in
	// read 1 byte each time
	// pull them from our opened picture
	// now let's change the offset
	offset += sizeof(header);
	
	
	// now we should check to see if the picture is formatted right
	
	if(header.appMarker != 0xE1FF)
	{
		printf("Improperly formatted!\n");
		printf("%hx\n", header.appMarker);
		return 1;
	}
	/*else
	{
		printf("Right formatting!\n"); // another dugging line!
	}*/
	
	// neat so if it's right, sweet-o
	// now we gotta check for endiannesssssss
	// which is easy seeing that it's stuffed into
	// a 2 length char array
	// just gott see if it's II~
	
	if(strcmp(header.endianness, "II") == 1)
	{
		printf("No support for big endian, sorry doodz\n");
		return 1;
	}
	/*else
	{
		printf("Aaaaay lmao small endian :D\n"); // just some silly debugging lines
	}*/
	
	// proper endianness is now confirmed
	// NOW TO MOVE ON
	// so we're going to find an unsigned short for the count
	// so let's make that
	// let's also make sure we're at offset 20
	//printf("Offset: %d\n", offset); // just a check for offset 20
	unsigned short count; // found at offset 20
	// now let's read it in considering where we are
	// NOW WE ARE AT 20
	// BLEH HAD TO CHANGE VERSION FROM INT TO SHORT TO MAKE IT WORK
	// TABLEFLIP
	// YES THAT DOES SAY TABLEFLIP BECAUSE I COULDN'T EVEN PUT IN THE EMOJI
	// GRAAAH OKAY WAS HOPING TO BE EFFICIENT/CLEAR LIKE THAT BUT OKAY
	// FINE
	// LET'S READ IN THE COUNT
	// end ragerant.exe
	
	// okay
	// let's read in count
	fread(&count, sizeof(count), 1, picture); // so we're going to tuck in the next thing
	// into count from picture, size of count so that's easy, 1 time precisely
	
	// printf("count is: %d\n", count); // just another debugging line that tells count
	// okay well
	// now we have our count variable
	// time to start reading in our tag variables
	// count number of times
	
	int i = 0;
	offset = 0; // let's just ressset this
	// we'll also need to create a few vars to hold our values
	// since we know we'll be reading in strings
	// as in, the manufacturer data, we should prepare for that
	// thus, let's create a char array of strings
	char *tagData[50]; // 50 sounds good enough?
	unsigned short EXIFsubblockaddress;
	
	for(i = 0; i < count; i++)
	{
		fread(&pictag, sizeof(pictag), 1, picture); // like before, let's start
		// reading in our TIFF tags into the struct
		
		// okay so we know
		// that offset 0
		// will give us our ID
		// so now we have to check what tagID (our first struct var) is
		// and use that to determine what to do
		// ALSO
		// because we will be iterating through
		// we may want to keep our place in the file
		// since we will be hopping around everywhere
		// we'll need to seek back to our previous location
		// as in, we'll need to keep track of our offsets
		
		offset = ftell(picture);
		
		
		
		if(pictag.tagID == 0x010F)
		{
			// this means we're finding the manufacturing's string!
			// first we need to move over to the actual place
			// by using the tag's given offset + 12
			// so let's seek there
			fseek(picture, pictag.TIFFoffset + 12, SEEK_SET);
			fread(&tagData, sizeof(char), pictag.itemNum, picture);
			// read in to tagData, size of the character, and then do it the amount of times
			// that there are objects
			// since we know this is the manufacturer:
			printf("Manufacturer: \t\t%s\n", tagData);
		}
		else if(pictag.tagID == 0x0110)
		{
			fseek(picture, pictag.TIFFoffset + 12, SEEK_SET);
			fread(&tagData, sizeof(char), pictag.itemNum, picture);
			printf("Camera Model String: \t%s\n", tagData);
		}
		else if(pictag.tagID == 0x8769)
		{
			// so we can stop reading in here and start reading off teh tags
			fseek(picture, pictag.TIFFoffset + 12, SEEK_SET);
			// so we'll head to the place first
			// and now we need to pull our offset
			// from the read data
			// so first, let's ready in said data
			// our read in can look differet
			// seeing that we don't need to read in a "string value"
			// what we need to read in here is a short
			// and then add 12 to it so we have the correct position
			fread(&EXIFsubblockaddress, sizeof(short), 1, picture);
			// so now that we read it, let's jump over
			int y = 0;
			int EXIFoffset;
			// we will also need a new TIFF tag, as we will continue reading in more 
			//12 byte TIFF tags from this offset
			struct TIFFtag EXIFsubs;
			// 3 of our new values will be unsigned ints
			// well 6, but 2*3 so whatever
			// so let's make those here
			unsigned int unsigInt1 = 0;
			unsigned int unsigInt2 = 0; 
			// for exposure speed, F-stop, and Lens focal length
			
			for(y=0; y < EXIFsubblockaddress; y++)
			{
				// now we loop through and start reading everything!
				fread(&EXIFsubs, sizeof(EXIFsubs), 1, picture);
				// also we need another temp location
				EXIFoffset = ftell(picture);
				
				// however, type 4s are directly included
				// so we don't have to seek yaaaay
				if(EXIFsubs.tagID == 0xA002)
				{
					// for these, we can print the last 4 bytes right off the bat
					// AKA the offset here
					//printf("Width!\n");
					printf("Width: \t\t\t%d pixels\n", EXIFsubs.TIFFoffset);
				}
				
				if(EXIFsubs.tagID == 0xA003)
				{
					printf("Height: \t\t%d pixels\n", EXIFsubs.TIFFoffset);
				}
				
				if(EXIFsubs.tagID == 0x8827)
				{
					printf("ISO: \t\t\tISO %d\n", EXIFsubs.TIFFoffset);
				}
				
				if(EXIFsubs.tagID == 0x829a)
				{
					// so we have 2 unsigned ints
					// need to read them both
					// but first we need to seek to that place
					fseek(picture, EXIFsubs.TIFFoffset+12, SEEK_SET);
					fread(&unsigInt1, sizeof(int), 1, picture);
					fread(&unsigInt2, sizeof(int), 1, picture);
					printf("Exposure Time: \t\t%d/%d seconds\n", unsigInt1, unsigInt2);
				}
				if(EXIFsubs.tagID == 0x829d)
				{
					// so we have 2 unsigned ints
					// need to read them both
					// but first we need to seek to that place
					fseek(picture, EXIFsubs.TIFFoffset+12, SEEK_SET);
					fread(&unsigInt1, sizeof(int), 1, picture);
					fread(&unsigInt2, sizeof(int), 1, picture);
					printf("F-stop: \t\tf/%d.%d\n", unsigInt1, unsigInt2);
				}
				if(EXIFsubs.tagID == 0x920A)
				{
					// so we have 2 unsigned ints
					// need to read them both
					// but first we need to seek to that place
					fseek(picture, EXIFsubs.TIFFoffset+12, SEEK_SET);
					fread(&unsigInt1, sizeof(int), 1, picture);
					fread(&unsigInt2, sizeof(int), 1, picture);
					printf("Lens Focal Length: \t%d%d mm\n", unsigInt1, unsigInt2);
				}
				if(EXIFsubs.tagID == 0x9003)
				{
					// so we have 2 unsigned ints
					// need to read them both
					// but first we need to seek to that place
					fseek(picture, EXIFsubs.TIFFoffset+12, SEEK_SET);
					fread(&tagData, sizeof(char), EXIFsubs.itemNum, picture);
					printf("Date Taken: \t\t%s\n", tagData);
				}
				fseek(picture, EXIFoffset, SEEK_SET);
			}
			
			
			
			//printf("Zoom zoom?", tagData); // debugging line
			i = count;
		}
		
		// need to reset back to where we were to get back to reading all the tags
		fseek(picture, offset, SEEK_SET);
		
		
	}
	
	
	return 0;
	
		
	
	
}