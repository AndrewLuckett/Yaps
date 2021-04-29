'''
Python script to generate values for
std::unordered_map<uint, ParticleProperties> ParticleTypes = {
in game/ParticleProperties.h

This makes it easier to reorder the structs values for better packing
'''


order = ["gravity", "solid", "movable", "fluid", "flammable", "boilable",
         "hot", "decay", "name"]

particles = {"Air": {"colour": "0x000000"},
             "Sand": {"colour": "0xeecc99", "gravity": 2, "solid": 1, "movable": 1,
                      "fluid": 0, "flammable": 0, "hot": 0, "decay": 0},
             "Water": {"colour": "0x0f0fff", "gravity": 2, "solid": 1, "movable": 1,
                      "fluid": 1, "flammable": 0, "boilable": 1, "hot": 0, "decay": 0},
             "Smoke": {"colour": "0x404040", "gravity": 3, "solid": 0, "movable": 1,
                      "fluid": 1, "flammable": 0, "boilable": 0, "hot": 0, "decay": 1},
             "Steam": {"colour": "0xa0a0a0", "gravity": 3, "solid": 0, "movable": 1,
                      "fluid": 1, "flammable": 0, "boilable": 0, "hot": 0, "decay": 1}
             }

def main():
    enu = ""
    out = ""
    global k,v
    for k, v in particles.items():
        enu += k + " = " + v["colour"] + ",\n"
        out += "{(uint) ParticleNames::" + k + ", {"
        for i in order:
            if i == "name":
                out += '"' + k + '"'
            else:
                out += str(v.get(i) or 0)
            out += ", "
        out = out[:-2]
        out += "}},\n"
    return enu, out
                

if __name__ == "__main__":
    e,o = main()
    print(e)
    print(o)
