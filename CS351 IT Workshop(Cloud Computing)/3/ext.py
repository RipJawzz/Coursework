import boto3
import creds
client=boto3.client('autoscaling')

check=[1,1,1,0]
'''
0-create launchconfig
1-create autoscaling group
2- put scaling policy
'''

if check[0]:
    startupscript = open(r"startscript.sh","r")
    Files=startupscript.read()
    response = client.create_launch_configuration(
        LaunchConfigurationName=creds.lc_name,
        ImageId=creds.ami_ID,
        SecurityGroups=[
            creds.sg
        ],
        UserData=Files,
        KeyName=creds.key_name,
        InstanceType='t2.micro',
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
        InstanceMonitoring={
            'Enabled': False
        },
    )

if check[1]:
    autoresponse = client.create_auto_scaling_group(
        AutoScalingGroupName=creds.asg,
        LaunchConfigurationName=creds.lc_name,
        MaxInstanceLifetime=2592000,
        MaxSize=3,
        MinSize=1,
        DesiredCapacity=1,
        VPCZoneIdentifier='subnet-9df405d1',
    )


if check[2]:
    response = client.put_scaling_policy(
    AutoScalingGroupName=creds.asg,
    PolicyName='ScalingPo',
    PolicyType='TargetTrackingScaling',
    AdjustmentType='ChangeInCapacity',
    EstimatedInstanceWarmup=60,
    TargetTrackingConfiguration={
        'PredefinedMetricSpecification': {
            'PredefinedMetricType': 'ASGAverageCPUUtilization',
        },
        'TargetValue': 80,
        'DisableScaleIn': False
    },
    Enabled=True,
)

