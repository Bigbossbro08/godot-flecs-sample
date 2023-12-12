extends Node


var world:World
var entityCount:int
var rng
@export var r:Rendering

func _ready() -> void:
	world = World.new()
	rng = RandomNumberGenerator.new()

func _process(_delta):
	if (Input.is_key_pressed(KEY_ENTER)):
		spawnEntity(1000)
		
	world.progress()
	$Label.text = ("FPS " + str(Engine.get_frames_per_second()) + " entity count: " + str(r.get_spawn_count()))

func spawnEntity(count):
	for i in count:
		r.spawn_entity(world,str("Entity",entityCount),
		rng.randf_range(-50.0, 50.0),
		rng.randf_range(0.0, 10.0),
		rng.randf_range(-50.0, 50.0),
		1,
		#rng.randf_range(-1, 1),
		#rng.randf_range(-0.1, 0.1),
		0,
		#rng.randf_range(-1, 1))
		0)
		entityCount+=1
