import os

prefix = """//
// Created by anchi on 28/07/2021.
//

#include "rover.h"


void defineRover( Composite &rover )
{
"""

suffix = "}"

Vcount = 0
VNcount = 0
VTcount = 0

class Material:
	def __init__(self, name):
		self.name = name
		self.shininess = None
		self.opacity = None
		self.imgPath = None
		self.ambient = []
		self.diffuse = []
		self.specular = []
		self.emission = []

class Drawable:
	def __init__(self, name):
		self.name = name
		self.smoothing = False
		self.material = None
		self.vertices = []
		self.texCoords = []
		self.normals = []
		self.faces = []

materials = []
objects = []


def matchBeginning(text, pattern):
	if text.startswith(pattern):
		return text.removeprefix(pattern).lstrip()
	
	else: return None

def parseMTL(text: str):
	for line in text.splitlines():
		if name := matchBeginning(line,"newmtl"):
			name = name.replace('.', '').lower()
			materials.append(Material(name))
		
		elif value := matchBeginning(line, "Ns"):
			materials[-1].shininess = float(value) * (128/1000)
		
		elif value := matchBeginning(line, "d"):
			materials[-1].opacity = float(value)
		
		elif path := matchBeginning(line, "map_Kd"):
			materials[-1].imgPath = path
		
		elif values := matchBeginning(line, "Ka"):
			x, y, z = [float(value) for value in values.split(' ')]
			materials[-1].ambient = [x, y, z]
		
		elif values := matchBeginning(line, "Kd"):
			x, y, z = [float(value) for value in values.split(' ')]
			materials[-1].diffuse = [x, y, z]
		
		elif values := matchBeginning(line, "Ks"):
			x, y, z = [float(value) for value in values.split(' ')]
			materials[-1].specular = [x, y, z]
		
		elif values := matchBeginning(line, "Ke"):
			x, y, z = [float(value) for value in values.split(' ')]
			materials[-1].emission = [x, y, z]

def parseOBJ(text):
	global Vcount, VTcount, VNcount

	for line in text.splitlines():
		if MTLpath := matchBeginning(line, "mtllib"):
			MTLfile = open(MTLpath, 'r')
			parseMTL(MTLfile.read())
			MTLfile.close()
		
		elif name := matchBeginning(line, "o"):
			name = name.split('_')[0]
			objects.append(Drawable(name))
			
			if len(objects) > 1:
				Vcount += len(objects[-2].vertices)
				VTcount += len(objects[-2].texCoords)
				VNcount += len(objects[-2].normals)
		
		elif smoothing := matchBeginning(line, "s"):
			objects[-1].smoothing = False if smoothing == "off" else True
		
		elif material := matchBeginning(line, "usemtl"):
			material = material.replace('.', '').lower()
			objects[-1].material = next((m for m in materials if m.name == material), None)

		elif values := matchBeginning(line, "vt"):
			x, y = [float(value) for value in values.split(' ')]
			objects[-1].texCoords.append([x, y])

		elif values := matchBeginning(line, "vn"):
			x, y, z = [float(value) for value in values.split(' ')]
			objects[-1].normals.append([x, y, z])

		elif values := matchBeginning(line, "v"):
			x, y, z = [float(value) for value in values.split(' ')]
			objects[-1].vertices.append([x, y, z])
		
		elif values := matchBeginning(line, "f"):
			objects[-1].faces.append([[int(value) - 1 for value in face.split('/')] for face in values.split(' ')])

			if len(objects) > 1:
				for index in objects[-1].faces[-1]:
					index[0] -= Vcount
					index[1] -= VTcount
					index[2] -= VNcount


def writeCPPCode(CPPfile):
	text = ""
	
	for material in materials:
		text += f"\tMaterial {material.name};\n"
		text += (f"\t{material.name}.shininess = {material.shininess};\n")
		text += (f"\t{material.name}.opacity = {material.opacity};\n")
		if material.imgPath: text += (f'\t{material.name}.setTexture("{material.imgPath}");\n')
		text += (f"\t{material.name}.ambient = array3f({material.ambient[0]}, {material.ambient[1]}, {material.ambient[2]});\n")
		text += (f"\t{material.name}.diffuse = array3f({material.diffuse[0]}, {material.diffuse[1]}, {material.diffuse[2]});\n")
		text += (f"\t{material.name}.specular = array3f({material.specular[0]}, {material.specular[1]}, {material.specular[2]});\n")
		text += (f"\t{material.name}.emission = array3f({material.emission[0]}, {material.emission[1]}, {material.emission[2]});\n\n")

	CPPfile.write(text + "\n")
	text = ""

	for object in objects:
		text = f"\tDrawable {object.name};\n"

		text += (f"\t{object.name}.setSmoothing({'true' if object.smoothing else 'false'});\n")
		text += (f"\t{object.name}.setMaterial({object.material.name});\n\n")
		
		for vertex in object.vertices:
			text += (f"\t{object.name}.addVertex(array3f({vertex[0]}, {vertex[1]}, {vertex[2]}));\n")
		
		text += (f"\n")

		for texCoord in object.texCoords:
			text += (f"\t{object.name}.addTexCoord({texCoord[0]}, {texCoord[1]});\n")
		
		text += (f"\n")
		
		for normal in object.normals:
			text += (f"\t{object.name}.addNormal(array3f({normal[0]}, {normal[1]}, {normal[2]}));\n")
		
		text += (f"\n")

		for face in object.faces:
			text += (f"\t{object.name}.addFacevtn({{")

			for point in face:
				text += (f"{{{point[0]}, {point[1]}, {point[2]}}}")
				if point is not face[-1]: text += (", ")
			
			text += (f"}});\n")
		
		CPPfile.write(text + "\n\n")
	
	text = ""
	
	for object in objects:
		text += f"\trover.addDrawable({object.name});\n"

	CPPfile.write(text)


OBJfile = open("C:\\Users\\anchi\\Desktop\\rover.obj", 'r')
os.chdir(os.path.dirname("C:\\Users\\anchi\\Desktop\\rover.obj"))
parseOBJ(OBJfile.read())
OBJfile.close()

CPPfile = open("/rover.cpp", 'w')
CPPfile.write(prefix)
writeCPPCode(CPPfile)
CPPfile.write(suffix)
CPPfile.close()