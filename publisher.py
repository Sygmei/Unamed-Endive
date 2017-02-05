import os

os.chdir("F:\\ENDIVE")


def read_version():
    v = ''
    with open('version.h') as version_file:
        content = version_file.readlines()
    v += content[16][content[16].index('=') + 2:-2] + '.'  # MAJOR
    v += content[17][content[17].index('=') + 2:-2] + '.'  # MINOR
    v += content[18][content[18].index('=') + 2:-2] + '-'  # BUILD
    v += content[19][content[19].index('=') + 2:-2] + ' '  # REVISION
    v += content[12][content[12].index('=') + 4:-3]        # STATUS
    return v


with open('inno_build.iss') as base:
    with open('build.iss', 'w') as new:
        formatted = base.readlines()
        formatted[4] = formatted[4][:-1] + '"{version}"\n'.format(version=read_version())
        formatted[5] = formatted[5][:-1] + '"{publisher}"\n'.format(publisher="Kubiangle (c) (r) tm")
        formatted[6] = formatted[6][:-1] + '"{website}"\n'.format(website='https://loodoor.github.io/Unamed-Endive')
        
        new.write("".join(formatted))

r = os.popen('"C:\\Program Files (x86)\\Inno Setup 5\\ISCC.exe" build.iss').read()
os.remove("build.iss")

input('\n'.join(r.split('\n')[-3:-1]))