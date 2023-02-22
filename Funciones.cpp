#include"Funciones.h"
#include<cstdint>
#include <iostream>
#include<fstream>
int Funciones::VerificacionDeArchivo(char* fileName){
  
   std::ifstream in(fileName);
   if(!in.is_open()){
      std::cerr<<"Error to open "<<fileName<<std::endl;
      return -1;

   }
   else{
       EjecutableWindows ew;
       long pos;
       
       in.read(reinterpret_cast<char*>(&ew),sizeof(EjecutableWindows));
       
       if(in.gcount()==sizeof(EjecutableWindows)){
             
           if(ew.id[1]==0x5a && ew.id[0]==0x4d){
            in.seekg(ew.offset);
            uint8_t verifcacion2[4];
            in.read(reinterpret_cast<char*>(&verifcacion2),sizeof(verifcacion2));
           if(in.gcount()==sizeof(verifcacion2)){
            if(verifcacion2[0]==0x50 &&verifcacion2[1]==0x45 && verifcacion2[2]==0x00 &&verifcacion2[3]==0x00){
            uint16_t machine;
            in.read(reinterpret_cast<char*>(&machine),sizeof(machine));
            if(machine==0x8664){
                std::cout<<"File Type: Windows Executable 64 bits"<<std::endl; 
            }
            else if(machine==0x14c){
                
             std::cout<<"File Type: Windows Executable 32 bits"<<std::endl; 
            }
            
            else{
              std::cout<<"File Type: Windows Executable <Unknown machine type>"<<std::endl; 
            }
               in.close();
             return 0;
           }
           else{
              std::cout<<"File Type: Windows Executable<Not PE>"<<std::endl;
               in.close(); 
               return 0;
             }
           
       }
       }
       }


       in.seekg(0,std::ios::beg);

       EjecutableLinux el;
       in.read(reinterpret_cast<char*>(&el),sizeof(EjecutableLinux));
       
       if(in.gcount()==sizeof(EjecutableLinux)){
           if(el.id[0]==0x7f && el.id[1]==0x45 && el.id[2]==0x4c && el.id[3]==0x46){
            std::cout<<"File Type: Linux Executable ";
            if(el.type==1){
                std::cout<<"32 bits"<<std::endl;
            }
            else if(el.type==2){
                std::cout<<"64 bits"<<std::endl;
            }
              in.close();
             return 0;
           }
           
       }
     in.seekg(0,std::ios::beg);

       GIF gif;
      
       in.read(reinterpret_cast<char*>(&gif),sizeof(GIF));
       if(in.gcount()==sizeof(GIF)){
           if(gif.id[0]==0x47 && gif.id[1]==0x49 && gif.id[2]==0x46 && gif.id[3]==0x38){
            std::cout<<"File Type: GIF  "<<"Width: "<<gif.width<<" Height: "<<gif.height<<std::endl;
             in.close();
            return 0;
           
       }
       }
    in.seekg(0,std::ios::beg);

       PNG png;
       in.read(reinterpret_cast<char*>(&png),sizeof(PNG));
       
       if(in.gcount()==sizeof(PNG)){
           if(png.id[0]==0x89 && png.id[1]==0x50 && png.id[2]== 0x4e && png.id[3]==0x47&& png.id[4]==0x0d && png.id[5]==0x0a && png.id[6]==0x1a && png.id[7]==0x0a){
            uint32_t widthBE= toLittleEndian(png.width[0],png.width[1],png.width[2],png.width[3]);
            uint32_t heightBE= toLittleEndian(png.height[0],png.height[1],png.height[2],png.height[3]);
            std::cout<<"File Type: PNG  "<<"Width: "<<widthBE<<" Height: "<<heightBE<<std::endl;
             in.close();
           
            return 0;
           
       }
       }
    in.seekg(0,std::ios::beg);

       BMP bmp;
       in.read(reinterpret_cast<char*>(&bmp),sizeof(BMP));
       
       if(in.gcount()==sizeof(BMP)){
       
           if(bmp.id[0]==0x42 && bmp.id[1]==0x4d){
            std::cout<<"File Type: BMP  "<<"Width: "<<bmp.width<<" Height: "<<bmp.height<<std::endl;
             in.close();
            return 0;
           
       }
       }
       
       in.seekg(0,std::ios::beg);
       JPG jpg;
       in.read(reinterpret_cast<char*>(&jpg),sizeof(JPG));
       in.close();
       if(in.gcount()==sizeof(JPG)){
          if(jpg.id[0]==0xFF && jpg.id[1]==0xD8 && jpg.id[2]==0xFF && jpg.id[3]==0xE0 && jpg.id[6]=='J' && jpg.id[7]=='F' && jpg.id[8]=='I' && jpg.id[9]=='F'){
         FILE *fjpg=fopen(fileName,"rb");
        
         fseek(fjpg,0,SEEK_END);
         long len=ftell(fjpg);
         fseek(fjpg,0,SEEK_SET);
      
        unsigned char buf[24]; 
        fread(buf,1,24,fjpg);
        if (buf[0]==0xFF && buf[1]==0xD8 && buf[2]==0xFF && buf[3]==0xE0 && buf[6]=='J' && buf[7]=='F' && buf[8]=='I' && buf[9]=='F')
        { long pos=2;
        while (buf[2]==0xFF)
        { if (buf[3]==0xC0 || buf[3]==0xC1 || buf[3]==0xC2 || buf[3]==0xC3 || buf[3]==0xC9 || buf[3]==0xCA || buf[3]==0xCB) break;
         pos += 2+(buf[4]<<8)+buf[5];
         if (pos+12>len){break;}
         fseek(fjpg,pos,SEEK_SET); fread(buf+2,1,12,fjpg);
         }
        }
  
        fclose(fjpg);

       if (buf[0]==0xFF && buf[1]==0xD8 && buf[2]==0xFF)
       { int y = (buf[7]<<8) + buf[8];
         int x = (buf[9]<<8) + buf[10];
         std::cout<<"File Type: JPG "<<" Width: "<<x<<" Height: "<<y<<std::endl;
     
         return 0;
      }
     }
    }

   
       in.open(fileName);
    
       in.seekg(0,std::ios::beg);
       TIFF tiff;
       in.read(reinterpret_cast<char*>(&tiff),sizeof(TIFF));
       
       if(in.gcount()==sizeof(TIFF)){
           if(tiff.id[0]==0x49 && tiff.id[1]==0x49 && tiff.id[2]==0x2a && tiff.id[3]==0x00){
            std::cout<<"File Type: TIFF  "<<std::endl;
             in.close();
            return 0;
           
       }
       }

       in.seekg(0,std::ios::beg);
       SVG svg;
       in.read(reinterpret_cast<char*>(&svg),sizeof(SVG));
      
       if(in.gcount()==sizeof(SVG)){
           if(svg.id[0]==0x3c && svg.id[1]==0x3f && svg.id[2]==0x78 && svg.id[3]==0x6d && svg.id[4]==0x6c){
            std::cout<<"File Type: SVG  "<<std::endl;
             in.close();
            return 0;
           
       }
       }

      in.seekg(0,std::ios::beg);
       ZIP zip;
       in.read(reinterpret_cast<char*>(&zip),sizeof(ZIP));
      
       if(in.gcount()==sizeof(ZIP)){
           if(zip.id[0]== 0x50 && zip.id[1]==0x4b && zip.id[2]== 0x03 && zip.id[3]==0x04){
            std::cout<<"File Type: ZIP  "<<std::endl;
             in.close();
            return 0;
           
       }
       }
    
     in.seekg(0,std::ios::beg);
       RAR rar;
       in.read(reinterpret_cast<char*>(&rar),sizeof(RAR));
    
       if(in.gcount()==sizeof(RAR)){
           if(rar.id[0]==0x52 && rar.id[1]==0x61 && rar.id[2]==0x72 && rar.id[3]==0x21 && rar.id[4]==0x1a && rar.id[5]==0x07 && rar.id[6]==0x00 ){
            std::cout<<"File Type: RAR  "<<std::endl;
             in.close();
            return 0;
           
       }
       }
     in.seekg(0,std::ios::beg);
       GZIP gzip;
       in.read(reinterpret_cast<char*>(&gzip),sizeof(GZIP));
      
       if(in.gcount()==sizeof(GZIP)){
           if(gzip.id[0]==0x1f && gzip.id[1]==0x8b && gzip.id[2]==0x08 ){
            std::cout<<"File Type: GZIP "<<std::endl;
             in.close();
            return 0;
           
       }
       }
   
       in.seekg(0,std::ios::beg);
       BZIP bzip;
       in.read(reinterpret_cast<char*>(&bzip),sizeof(BZIP));
       
       if(in.gcount()==sizeof(BZIP)){
           if(bzip.id[0]==0x42 && bzip.id[1]==0x5a && bzip.id[2]==0x68 ){
            std::cout<<"File Type: BZIP2  "<<std::endl;
             in.close();
            return 0;
           
       }
       }
      in.seekg(0,std::ios::beg);
       XZ xz;
       in.read(reinterpret_cast<char*>(&xz),sizeof(XZ));
     
       if(in.gcount()==sizeof(XZ)){
           if(xz.id[0]==0xfd && xz.id[1]==0x37 && xz.id[2]==0x7a && xz.id[3]==0x58 && xz.id[4]==0x5a && xz.id[5]==0x00 ){
            std::cout<<"File Type: XZ "<<std::endl;
             in.close();
            return 0;
           
       }
       }
        
   }
   
   std::cout<<fileName<<"<NOT VALID FILE>"<<std::endl;
   in.close();
   return -1;
}

uint32_t Funciones::toLittleEndian(uint8_t b1,uint8_t b2,uint8_t b3,uint8_t b4){
    uint32_t resultado;
    
    resultado= static_cast<uint32_t>(b1)<<24;
    resultado|= static_cast<uint32_t>(b2)<<16;
    resultado|= static_cast<uint32_t>(b3)<<8;
    resultado|= static_cast<uint32_t>(b4);

   
    return resultado;
}