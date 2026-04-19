import colorsys

def generate_palette(n=255):
    print("uint8_t colors[] = {  // palette")
    
    for i in range(n):
        h = i / n
        s = 1.0
        v = 1.0
        
        r, g, b = colorsys.hsv_to_rgb(h, s, v)
        
        r = int(r * 255)
        g = int(g * 255)
        b = int(b * 255)
        
        print(f"    0x{r:02X}, 0x{g:02X}, 0x{b:02X},")
    
    print("};")

generate_palette()