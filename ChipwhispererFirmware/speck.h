#ifndef SPECK_HEADER
#define SPECK_HEADER

#define ER64(x,y,k) (x=ROTR64(x,8), x+=y, x^=k, y=ROTL64(y,3), y^=x)
#define DR64(x,y,k) (y^=x, y=ROTR64(y,3), x^=k, x-=y, x=ROTL64(x,8))
#define ROTL64(x,r) (((x)<<(r)) | (x>>(64-(r))))
#define ROTR64(x,r) (((x)>>(r)) | ((x)<<(64-(r))))

// The same stuff for 32 bit

#define ROTL32(x,r) (((x)<<(r)) | (x>>(32-(r))))
#define ROTR32(x,r) (((x)>>(r)) | ((x)<<(32-(r))))

#define ER32(x,y,k) (x=ROTR32(x,8), x+=y, x^=k, y=ROTL32(y,3), y^=x)
#define DR32(x,y,k) (y^=x, y=ROTR32(y,3), x^=k, x-=y, x=ROTL32(x,8))

// The same stuff for 16 bit - these are the only required methods for Speck3264

#define ROTL16(x,r) (((x)<<(r)) | (x>>(16-(r))))
#define ROTR16(x,r) (((x)>>(r)) | ((x)<<(16-(r))))

#define ER16(x,y,k) (x=ROTR16(x,7), x+=y, x^=k, y=ROTL16(y,2), y^=x)
#define DR16(x,y,k) (y^=x, y=ROTR16(y,2), x^=k, x-=y, x=ROTL16(x,7))


#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define u64 uint64_t
void Words64ToBytes(u64 words[],u8 bytes[],int numwords);
void BytesToWords64(u8 bytes[],u64 words[],int numbytes);
void Speck128256KeySchedule(u64 K[],u64 rk[]);
void Speck128256Encrypt(u64 Pt[],u64 Ct[],u64 rk[]);
void Speck128256Decrypt(u64 Pt[],u64 Ct[],u64 rk[]);
void EncryptBlock(u8 pt[], u8 k[], u8 ct[]);
void Speck3264_EncryptBlock(u8 pt[], u8 k[], u8 ct[]);


// 32 bit versions functions
void Words32ToBytes(u32 words[],u8 bytes[],int numwords);
void BytesToWords32(u8 bytes[],u32 words[],int numbytes);


void Words16ToBytes(u16 words[],u8 bytes[],int numwords);
void BytesToWords16(u8 bytes[],u16 words[],int numbytes);

void Speck3264KeySchedule(u16 K[],u16 rk[]);
void Speck3264Encrypt(u16 Pt[],u16 Ct[],u16 rk[]);
void Speck3264Decrypt(u16 Pt[],u16 Ct[],u16 rk[]);
#endif
