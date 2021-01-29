
import bpy

from bpy_extras.io_utils import axis_conversion


global_matrix = axis_conversion(to_forward='-Y', to_up='-Z').to_4x4() * 100

def faceValues(face, mesh, matrix, color_layer, i):
    fv = []
    for verti in face.vertices:
        fv.append((global_matrix * mesh.vertices[verti].co)[:])
    for v, verti in enumerate(face.vertices):
        c = color_layer.data[i + v].color
        fv.append((c.r, c.g, c.b))
    return fv

def faceToLine(face):
    return " ".join([("%.6f %.6f %.6f" % v) for v in face] + ["\n"])

def write(filepath, triangulate=False):

    scene = bpy.context.scene

    objects = []

    for obj in bpy.context.selected_objects:

        me = obj.data
        if not me.tessfaces and me.polygons:
            me.calc_tessface()

        faces = []

        if me is not None:

            matrix = obj.matrix_world.copy()
            color_layer = me.vertex_colors["Col"]
            for i, face in enumerate(me.tessfaces):
                fv = faceValues(face, me, matrix, color_layer, i * 3)
                faces.append(fv)

        objects.append({'name': obj.name, 'faces': faces})

    # write the faces to a file
    for o in objects:
        file = open(filepath + o['name'] + '.raw', "w")
        res = ''
        for face in o['faces']:
            res += faceToLine(face)
        file.write(res)
        file.close()

write('/home/x/tmu/revzero/data/gfx/')
