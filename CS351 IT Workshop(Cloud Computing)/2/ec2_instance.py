import boto3
import creds

client =boto3.resource('ec2',region_name="us-east-1",aws_access_key_id=creds.aws_access_key_id,
         aws_secret_access_key=creds.aws_secret_access_key,aws_session_token=creds.aws_session_token)

script = open(r"startscript.sh","r")
Files=script.read()

EC2_instances = client.create_instances(
    BlockDeviceMappings=[
        {
            'DeviceName': '/dev/xvda',
            'Ebs': {
                'DeleteOnTermination': True,
                'VolumeSize': 8,
                'VolumeType': 'gp2'
            },
        },
    ],
    ImageId='ami-0c2b8ca1dad447f8a',
    InstanceType='t2.micro',
    KeyName=creds.key_name,
    MaxCount=1,
    MinCount=1,
    Monitoring={
        'Enabled': False
    },
    SecurityGroupIds=[
        creds.sg, 
    ],
    UserData=Files,
   
)
instance=EC2_instances[0]
print("new EC2 Instance is created",instance.id)
print(instance)
instance.wait_until_running()
print("running state")               
print(client.Instance(instance.id).public_dns_name)